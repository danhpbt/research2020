package com.xynotec.research2020.ui.imagefilter;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.Toolbar;
import androidx.lifecycle.ViewModelProvider;

import com.xynotec.dagger.BaseActivity;
import com.xynotec.research2020.BR;
import com.xynotec.research2020.R;
import com.xynotec.research2020.ViewModelProviderFactory;
import com.xynotec.research2020.databinding.ActivityImagefilterBinding;

import javax.inject.Inject;

public class ImageFilterActivity extends BaseActivity<ActivityImagefilterBinding, ImageFilterViewModel>
        implements ImageFilterViewModel.ImageFilterViewModelListener {

    @Inject
    ViewModelProviderFactory factory;

    private ImageFilterViewModel mImageFilterViewModel;

    @Override
    protected int getLayoutRes() {
        return R.layout.activity_imagefilter;
    }

    @Override
    public int getBindingVariable() {
        return BR.imgFilterVM;
    }

    @Override
    public ImageFilterViewModel getViewModel() {
        mImageFilterViewModel = new ViewModelProvider(this, factory).get(ImageFilterViewModel.class);
        return mImageFilterViewModel;
    }

    @Override
    public void onMessage(String msg) {
        Toast.makeText(this, msg, Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Toolbar toolbar = (Toolbar)findViewById(R.id.sub_toolbar);
        if (toolbar != null) {
            setSupportActionBar(toolbar);

            getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_action_back);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);

            toolbar.setNavigationOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    onBackPressed();
                }
            });
        }

        mImageFilterViewModel.setListener(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_img_filter, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId())
        {
            case R.id.menu_reload:
                mImageFilterViewModel.reload();
                break;

            case R.id.menu_antigrain:
                mImageFilterViewModel.antiGrain();
                break;

            case R.id.menu_grayScale:
                mImageFilterViewModel.grayScale();
                break;

            case R.id.menu_colorFilter:
                mImageFilterViewModel.colorFilter();
                break;

            case R.id.menu_gamma:
                mImageFilterViewModel.gamma();
                break;

            case R.id.menu_brightness:
                mImageFilterViewModel.brightness();
                break;

            case R.id.menu_contrast:
                mImageFilterViewModel.contrast();
                break;

            case R.id.menu_invert:
                mImageFilterViewModel.invert();
                break;

            case R.id.menu_smooth:
                mImageFilterViewModel.smooth();
                break;

            case R.id.menu_gaussianBlur:
                mImageFilterViewModel.gaussianBlur();
                break;

            case R.id.menu_meanRemoval:
                mImageFilterViewModel.meanRemoval();
                break;

            case R.id.menu_sharpen:
                mImageFilterViewModel.sharpen();
                break;

            case R.id.menu_embossLaplacian:
                mImageFilterViewModel.embossLaplacian();
                break;

            case R.id.menu_edgeDetect:
                mImageFilterViewModel.edgeDetect();
                break;

            case R.id.menu_flip:
                mImageFilterViewModel.flip();
                break;

            case R.id.menu_randomJitter:
                mImageFilterViewModel.randomJitter();
                break;

            case R.id.menu_swirl:
                mImageFilterViewModel.swirl();
                break;

            case R.id.menu_sphere:
                mImageFilterViewModel.sphere();
                break;

            case R.id.menu_timeWarp:
                mImageFilterViewModel.timeWarp();
                break;

            case R.id.menu_moire:
                mImageFilterViewModel.moire();
                break;

            case R.id.menu_water:
                mImageFilterViewModel.water();
                break;

            case R.id.menu_pixelate:
                mImageFilterViewModel.pixelate();
                break;

            case R.id.menu_fishEye:
                mImageFilterViewModel.fishEye();
                break;

            case R.id.menu_bokehEffect:
                mImageFilterViewModel.bokehEffects();
                break;

            case R.id.menu_tube:
                mImageFilterViewModel.tube();
                break;
            
            case R.id.menu_mytube:
                mImageFilterViewModel.myTube();
                break;
    
            case R.id.menu_inkSketch:
                mImageFilterViewModel.inkSketch();
                break;
    
            case R.id.menu_edgeDetector:
                mImageFilterViewModel.edgeDetector();
                break;
    
            case R.id.menu_edgeMaster:
                mImageFilterViewModel.edgeMaster();
                break;
    
            case R.id.menu_toonEffect:
                mImageFilterViewModel.toonEffect();
                break;
    
            case R.id.menu_oilEffect:
                mImageFilterViewModel.oilEffect();
                break;
    
            case R.id.menu_pastelEffect:
                mImageFilterViewModel.pastelEffect();
                break;
    
            case R.id.menu_dreamEffect:
                mImageFilterViewModel.dreamEffect();
                break;
    
            case R.id.menu_smearEffect:
                mImageFilterViewModel.smearEffect();
                break;

            case R.id.menu_smearEffectPDN:
                mImageFilterViewModel.smearEffectPDN();
                break;

            case R.id.menu_gaussianBlurPDN:
                mImageFilterViewModel.gaussianBlurPDN();
                break;
    
            case R.id.menu_glowEffectPDN:
                mImageFilterViewModel.glowEffectPDN();
                break;

            case R.id.menu_jitterEffect_PDN:
                mImageFilterViewModel.jitterEffectPDN();
                break;
    
            case R.id.menu_stichEffect_PDN:
                mImageFilterViewModel.stichEffectPDN();
                break;

            default:
                return super.onOptionsItemSelected(item);
        }
        return true;
    }
}
